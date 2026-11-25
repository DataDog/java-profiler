---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 03:20:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795594598 34
1795594603 34
1795594608 34
1795594613 34
1795594618 34
1795594623 34
1795594628 34
1795594633 34
1795594638 34
1795594643 34
1795594648 34
1795594653 34
1795594658 34
1795594663 34
1795594668 34
1795594673 34
1795594678 34
1795594683 34
1795594688 34
1795594693 34
```
</details>

---

