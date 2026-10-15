---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 09:27:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 8 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792070519 48
1792070524 48
1792070529 48
1792070534 48
1792070539 48
1792070544 48
1792070549 48
1792070554 48
1792070559 48
1792070564 48
1792070569 48
1792070574 46
1792070579 46
1792070584 46
1792070589 46
1792070594 46
1792070599 46
1792070604 46
1792070609 46
1792070614 46
```
</details>

---

