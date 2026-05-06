---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-06 10:50:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 10 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 60-81 cores)</summary>

```
1778078730 77
1778078735 77
1778078740 77
1778078745 77
1778078750 77
1778078755 77
1778078760 81
1778078765 81
1778078770 81
1778078775 81
1778078780 81
1778078785 81
1778078790 72
1778078795 72
1778078800 72
1778078805 72
1778078810 60
1778078815 60
1778078820 60
1778078825 60
```
</details>

---

