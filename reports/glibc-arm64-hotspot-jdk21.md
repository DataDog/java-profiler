---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-18 01:04:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1792299673 40
1792299678 40
1792299683 40
1792299688 40
1792299693 40
1792299698 40
1792299703 40
1792299708 40
1792299713 40
1792299718 40
1792299723 40
1792299728 40
1792299734 40
1792299739 40
1792299744 40
1792299749 40
1792299754 40
1792299759 40
1792299764 40
1792299769 40
```
</details>

---

