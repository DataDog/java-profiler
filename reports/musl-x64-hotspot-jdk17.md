---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 18:25:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1792707712 92
1792707717 92
1792707722 92
1792707727 92
1792707732 94
1792707737 94
1792707742 94
1792707747 94
1792707752 94
1792707757 94
1792707762 94
1792707767 94
1792707772 94
1792707777 94
1792707782 94
1792707788 94
1792707793 94
1792707798 94
1792707803 94
1792707808 94
```
</details>

---

