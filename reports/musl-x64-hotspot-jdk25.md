---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:11:48 EST

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 13 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 44-69 cores)</summary>

```
1770134737 44
1770134742 44
1770134747 44
1770134752 44
1770134757 44
1770134762 44
1770134767 44
1770134772 44
1770134777 44
1770134782 44
1770134787 44
1770134792 44
1770134797 65
1770134802 65
1770134807 65
1770134812 65
1770134817 69
1770134822 69
1770134827 65
1770134832 65
```
</details>

---

