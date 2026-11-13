---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 33-35 cores)</summary>

```
1794567531 33
1794567536 33
1794567541 33
1794567546 33
1794567551 33
1794567556 33
1794567561 33
1794567566 33
1794567571 33
1794567576 33
1794567581 33
1794567586 33
1794567591 33
1794567596 33
1794567601 33
1794567606 35
1794567611 35
1794567616 35
1794567621 35
1794567626 35
```
</details>

---

