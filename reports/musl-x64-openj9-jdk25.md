---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 08:53:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 24-53 cores)</summary>

```
1795614497 27
1795614502 27
1795614507 27
1795614512 27
1795614517 27
1795614522 27
1795614527 27
1795614532 27
1795614537 24
1795614542 24
1795614547 24
1795614552 24
1795614557 24
1795614562 24
1795614568 24
1795614573 24
1795614578 24
1795614583 24
1795614588 24
1795614593 24
```
</details>

---

