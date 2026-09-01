---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-01 15:37:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1788291128 54
1788291133 54
1788291138 54
1788291143 54
1788291148 59
1788291153 59
1788291158 59
1788291163 59
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
```
</details>

---

