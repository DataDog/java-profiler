---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:32:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 63-76 cores)</summary>

```
1789737652 76
1789737657 76
1789737662 76
1789737667 76
1789737672 76
1789737677 76
1789737682 76
1789737687 76
1789737692 76
1789737698 76
1789737703 76
1789737708 76
1789737713 63
1789737718 63
1789737723 63
1789737728 63
1789737733 63
1789737738 63
1789737743 63
1789737748 63
```
</details>

---

