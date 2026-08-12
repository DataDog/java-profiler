---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 7 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 7-30 cores)</summary>

```
1786523556 30
1786523561 30
1786523566 30
1786523571 30
1786523576 30
1786523581 30
1786523586 30
1786523591 30
1786523596 30
1786523601 30
1786523606 10
1786523611 10
1786523616 10
1786523621 10
1786523626 10
1786523631 10
1786523636 10
1786523641 10
1786523646 10
1786523651 10
```
</details>

---

