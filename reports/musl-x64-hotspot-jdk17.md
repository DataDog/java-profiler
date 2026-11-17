---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 10:58:04 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1794930675 87
1794930680 87
1794930686 87
1794930691 87
1794930696 87
1794930701 87
1794930706 87
1794930711 87
1794930716 87
1794930721 87
1794930726 87
1794930731 85
1794930736 85
1794930741 85
1794930746 85
1794930751 85
1794930756 85
1794930761 85
1794930766 85
1794930771 85
```
</details>

---

