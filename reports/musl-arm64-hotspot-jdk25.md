---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 08:24:28 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 47-52 cores)</summary>

```
1787055600 48
1787055605 48
1787055610 52
1787055615 52
1787055620 52
1787055625 52
1787055630 52
1787055635 52
1787055640 52
1787055645 52
1787055650 52
1787055655 52
1787055660 52
1787055665 52
1787055670 52
1787055675 52
1787055680 52
1787055685 52
1787055690 52
1787055695 52
```
</details>

---

