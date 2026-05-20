---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-20 05:49:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 59-65 cores)</summary>

```
1779270342 63
1779270347 63
1779270352 63
1779270357 63
1779270362 63
1779270367 63
1779270372 63
1779270377 63
1779270382 59
1779270387 59
1779270392 59
1779270397 59
1779270402 59
1779270407 59
1779270412 59
1779270417 59
1779270422 59
1779270427 59
1779270432 65
1779270437 65
```
</details>

---

