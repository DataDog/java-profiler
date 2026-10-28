---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:12:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1793185668 47
1793185673 47
1793185678 47
1793185683 47
1793185688 47
1793185693 47
1793185698 47
1793185703 47
1793185708 47
1793185713 47
1793185718 47
1793185723 47
1793185728 47
1793185733 45
1793185738 45
1793185743 45
1793185748 45
1793185753 45
1793185758 45
1793185763 45
```
</details>

---

