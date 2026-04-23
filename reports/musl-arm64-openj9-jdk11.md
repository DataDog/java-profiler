---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:22:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 11 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 979 |
| Sample Rate | 16.32/sec |
| Health Score | 1020% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 47-59 cores)</summary>

```
1776953845 54
1776953850 54
1776953855 54
1776953860 59
1776953865 59
1776953870 59
1776953875 59
1776953880 59
1776953885 59
1776953890 47
1776953895 47
1776953900 47
1776953905 47
1776953910 47
1776953915 47
1776953920 47
1776953925 47
1776953930 47
1776953935 47
1776953940 47
```
</details>

---

