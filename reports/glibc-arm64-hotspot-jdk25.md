---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-23 09:28:37 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776950572 64
1776950577 64
1776950582 64
1776950587 64
1776950592 64
1776950597 64
1776950602 64
1776950607 64
1776950612 64
1776950617 64
1776950622 64
1776950627 64
1776950632 64
1776950637 64
1776950642 64
1776950647 64
1776950652 64
1776950657 64
1776950662 64
1776950667 64
```
</details>

---

