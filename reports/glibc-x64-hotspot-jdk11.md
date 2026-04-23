---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 09:28:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 23-61 cores)</summary>

```
1776950592 61
1776950597 61
1776950602 61
1776950607 61
1776950612 61
1776950617 61
1776950622 61
1776950627 61
1776950632 61
1776950637 61
1776950642 61
1776950647 61
1776950652 41
1776950657 41
1776950662 41
1776950667 41
1776950672 32
1776950677 32
1776950682 23
1776950687 23
```
</details>

---

