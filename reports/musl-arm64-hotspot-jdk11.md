---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:37:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 383 |
| Sample Rate | 6.38/sec |
| Health Score | 399% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790771580 48
1790771585 48
1790771590 43
1790771595 43
1790771600 43
1790771605 43
1790771610 43
1790771615 43
1790771620 43
1790771625 43
1790771630 43
1790771635 43
1790771640 43
1790771645 43
1790771650 43
1790771655 43
1790771660 43
1790771665 48
1790771670 48
1790771675 48
```
</details>

---

