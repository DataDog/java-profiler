---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 14:11:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (2 unique values: 43-45 cores)</summary>

```
1793819170 43
1793819175 43
1793819181 43
1793819186 43
1793819191 43
1793819196 43
1793819201 43
1793819206 43
1793819211 43
1793819216 43
1793819221 43
1793819226 43
1793819231 43
1793819236 43
1793819241 43
1793819246 43
1793819251 43
1793819256 43
1793819261 43
1793819266 45
```
</details>

---

