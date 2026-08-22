---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-22 11:45:51 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1787413233 66
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
```
</details>

---

