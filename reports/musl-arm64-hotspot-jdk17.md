---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 14:20:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 10 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787422597 43
1787422602 43
1787422607 43
1787422613 43
1787422618 43
1787422623 48
1787422628 48
1787422633 48
1787422638 48
1787422643 48
1787422648 48
1787422653 48
1787422658 48
1787422663 48
1787422668 48
1787422673 48
1787422678 48
1787422683 48
1787422688 48
1787422693 48
```
</details>

---

