---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:56:11 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (3 unique values: 74-91 cores)</summary>

```
1793890198 87
1793890203 87
1793890208 87
1793890213 87
1793890218 87
1793890223 87
1793890228 87
1793890233 87
1793890238 87
1793890243 87
1793890248 87
1793890253 91
1793890258 91
1793890263 91
1793890268 91
1793890273 91
1793890278 91
1793890283 91
1793890288 91
1793890293 91
```
</details>

---

