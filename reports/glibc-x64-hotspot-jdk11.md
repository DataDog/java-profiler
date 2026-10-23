---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 10:56:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1792767127 27
1792767132 27
1792767137 27
1792767142 27
1792767147 27
1792767152 29
1792767157 29
1792767162 29
1792767167 29
1792767172 29
1792767177 29
1792767182 29
1792767187 29
1792767192 29
1792767197 29
1792767202 29
1792767207 29
1792767212 29
1792767217 29
1792767222 29
```
</details>

---

