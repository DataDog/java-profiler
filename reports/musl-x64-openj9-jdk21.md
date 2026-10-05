---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 11:50:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 78-86 cores)</summary>

```
1791215128 86
1791215133 86
1791215138 86
1791215143 86
1791215148 86
1791215153 86
1791215159 86
1791215164 84
1791215169 84
1791215174 84
1791215179 84
1791215184 80
1791215189 80
1791215194 80
1791215199 80
1791215204 80
1791215209 80
1791215214 80
1791215219 80
1791215224 78
```
</details>

---

