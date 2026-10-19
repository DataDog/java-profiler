---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 09:36:02 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 14 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792416521 51
1792416526 51
1792416531 51
1792416536 51
1792416541 51
1792416546 51
1792416551 51
1792416556 51
1792416561 64
1792416566 64
1792416571 64
1792416576 64
1792416581 64
1792416586 64
1792416591 64
1792416596 64
1792416601 64
1792416606 64
1792416611 64
1792416616 64
```
</details>

---

