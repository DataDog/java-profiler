---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 12:59:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 22-30 cores)</summary>

```
1793120143 30
1793120148 30
1793120153 30
1793120158 30
1793120163 30
1793120168 30
1793120173 30
1793120178 30
1793120183 30
1793120188 30
1793120193 30
1793120198 30
1793120203 30
1793120208 30
1793120213 30
1793120218 22
1793120223 22
1793120228 22
1793120233 22
1793120238 22
```
</details>

---

