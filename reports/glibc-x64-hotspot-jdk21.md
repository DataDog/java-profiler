---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 09:53:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 12 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1770130138 79
1770130143 79
1770130148 79
1770130153 72
1770130158 72
1770130163 72
1770130168 72
1770130173 72
1770130178 72
1770130183 72
1770130188 72
1770130193 72
1770130198 72
1770130204 72
1770130209 72
1770130214 72
1770130219 72
1770130224 72
1770130229 77
1770130234 77
```
</details>

---

