---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 169 |
| Sample Rate | 2.82/sec |
| Health Score | 176% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 59-72 cores)</summary>

```
1795001502 72
1795001507 72
1795001512 63
1795001517 63
1795001522 63
1795001527 63
1795001532 63
1795001537 63
1795001542 63
1795001547 63
1795001552 61
1795001557 61
1795001562 61
1795001567 61
1795001572 61
1795001577 61
1795001582 61
1795001587 61
1795001592 59
1795001598 59
```
</details>

---

