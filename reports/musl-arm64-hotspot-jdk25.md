---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-23 21:22:04 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 13 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 43-46 cores)</summary>

```
1787534307 46
1787534312 46
1787534317 46
1787534322 46
1787534327 46
1787534332 46
1787534337 46
1787534342 46
1787534347 46
1787534353 46
1787534358 46
1787534363 46
1787534368 43
1787534373 43
1787534378 43
1787534383 43
1787534388 43
1787534393 43
1787534398 43
1787534403 43
```
</details>

---

