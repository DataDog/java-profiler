---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-07 10:19:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 10 |
| Allocations | 203 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794064541 43
1794064546 43
1794064551 43
1794064556 43
1794064561 43
1794064566 43
1794064571 43
1794064576 43
1794064581 43
1794064586 43
1794064591 43
1794064596 43
1794064601 43
1794064606 43
1794064611 43
1794064616 43
1794064621 43
1794064626 43
1794064631 48
1794064636 48
```
</details>

---

