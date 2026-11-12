---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 08:03:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 69-93 cores)</summary>

```
1794488369 93
1794488374 93
1794488379 93
1794488384 93
1794488389 93
1794488394 93
1794488399 91
1794488404 91
1794488409 91
1794488414 91
1794488419 91
1794488424 91
1794488429 89
1794488434 89
1794488439 89
1794488444 89
1794488449 89
1794488454 69
1794488459 69
1794488464 69
```
</details>

---

