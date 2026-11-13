---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 06:03:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 46-50 cores)</summary>

```
1794567566 46
1794567571 46
1794567576 46
1794567581 48
1794567586 48
1794567591 48
1794567596 48
1794567601 48
1794567606 48
1794567611 48
1794567616 48
1794567621 48
1794567626 48
1794567631 48
1794567636 48
1794567641 48
1794567646 48
1794567651 48
1794567656 48
1794567661 50
```
</details>

---

