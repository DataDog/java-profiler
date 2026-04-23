---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-23 09:28:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 12 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 63-94 cores)</summary>

```
1776950592 94
1776950597 94
1776950602 94
1776950607 94
1776950612 94
1776950617 94
1776950622 94
1776950627 94
1776950632 94
1776950637 94
1776950642 94
1776950647 63
1776950652 63
1776950657 63
1776950662 63
1776950667 63
1776950672 63
1776950677 63
1776950682 63
1776950687 63
```
</details>

---

