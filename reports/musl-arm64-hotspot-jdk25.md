---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 05:26:36 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 9 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1789723353 32
1789723358 32
1789723363 32
1789723368 32
1789723373 32
1789723378 32
1789723383 12
1789723388 12
1789723393 12
1789723398 12
1789723403 12
1789723408 12
1789723413 12
1789723418 12
1789723423 12
1789723428 12
1789723433 12
1789723438 12
1789723443 12
1789723448 12
```
</details>

---

