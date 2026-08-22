---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-22 11:45:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787413238 66
1787413243 66
1787413248 66
1787413253 66
1787413258 66
1787413263 66
1787413268 66
1787413273 64
1787413278 64
1787413283 64
1787413288 64
1787413293 64
1787413298 64
1787413303 64
1787413308 64
1787413313 64
1787413318 66
1787413323 66
1787413328 66
1787413333 66
```
</details>

---

