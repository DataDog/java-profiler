---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 12:30:29 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 279 |
| Sample Rate | 4.65/sec |
| Health Score | 291% |
| Threads | 12 |
| Allocations | 173 |

<details>
<summary>CPU Timeline (2 unique values: 19-31 cores)</summary>

```
1790785532 19
1790785537 31
1790785542 31
1790785547 31
1790785552 31
1790785557 31
1790785562 31
1790785567 31
1790785572 31
1790785577 31
1790785582 31
1790785587 31
1790785592 31
1790785597 31
1790785602 31
1790785607 31
1790785612 31
1790785617 31
1790785622 31
1790785627 31
```
</details>

---

