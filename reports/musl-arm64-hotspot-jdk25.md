---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-25 06:56:12 EDT

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
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 13 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792925332 46
1792925337 46
1792925342 46
1792925347 46
1792925352 46
1792925357 46
1792925362 46
1792925367 48
1792925372 48
1792925377 48
1792925382 48
1792925387 48
1792925392 48
1792925397 48
1792925402 48
1792925407 48
1792925412 48
1792925417 48
1792925422 48
1792925427 48
```
</details>

---

