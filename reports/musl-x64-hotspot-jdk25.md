---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:51:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1795610757 77
1795610762 77
1795610767 77
1795610772 77
1795610777 77
1795610782 77
1795610787 79
1795610792 79
1795610797 75
1795610802 75
1795610807 75
1795610812 75
1795610817 75
1795610822 75
1795610827 75
1795610832 75
1795610837 75
1795610842 75
1795610847 75
1795610852 75
```
</details>

---

