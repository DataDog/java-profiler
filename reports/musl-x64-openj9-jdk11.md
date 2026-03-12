---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-12 11:39:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1026 |
| Sample Rate | 17.10/sec |
| Health Score | 1069% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1773329642 94
1773329647 94
1773329652 94
1773329657 94
1773329662 92
1773329667 92
1773329672 92
1773329677 92
1773329682 92
1773329687 92
1773329692 92
1773329697 92
1773329702 94
1773329707 94
1773329712 94
1773329717 94
1773329722 94
1773329727 94
1773329732 94
1773329737 94
```
</details>

---

