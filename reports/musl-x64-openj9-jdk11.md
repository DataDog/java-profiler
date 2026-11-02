---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:41:18 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 38-57 cores)</summary>

```
1793633721 38
1793633726 38
1793633731 52
1793633736 52
1793633741 52
1793633746 52
1793633751 52
1793633756 52
1793633761 52
1793633767 57
1793633772 57
1793633777 57
1793633782 57
1793633787 57
1793633792 57
1793633797 57
1793633802 57
1793633807 55
1793633812 55
1793633817 55
```
</details>

---

