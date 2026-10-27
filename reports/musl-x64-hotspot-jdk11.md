---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 11:47:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1793115737 79
1793115742 79
1793115747 79
1793115752 79
1793115757 79
1793115762 79
1793115767 79
1793115772 79
1793115777 79
1793115782 79
1793115787 79
1793115792 81
1793115797 81
1793115802 81
1793115807 79
1793115812 79
1793115817 79
1793115822 79
1793115827 79
1793115832 79
```
</details>

---

