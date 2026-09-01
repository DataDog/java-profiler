---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-01 15:37:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1788291153 64
1788291158 64
1788291163 64
1788291168 64
1788291173 64
1788291178 64
1788291183 64
1788291188 64
1788291193 64
1788291198 64
1788291203 64
1788291208 64
1788291213 64
1788291218 64
1788291223 64
1788291228 64
1788291233 64
1788291238 44
1788291243 44
1788291248 44
```
</details>

---

