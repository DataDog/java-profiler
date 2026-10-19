---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 05:04:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 11 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (2 unique values: 28-38 cores)</summary>

```
1792400133 38
1792400138 38
1792400143 38
1792400148 38
1792400153 38
1792400158 38
1792400163 38
1792400168 28
1792400173 28
1792400178 28
1792400183 28
1792400188 28
1792400193 28
1792400198 28
1792400203 28
1792400208 28
1792400213 28
1792400218 28
1792400223 28
1792400228 28
```
</details>

---

