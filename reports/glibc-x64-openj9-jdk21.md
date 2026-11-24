---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 05:51:09 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795517193 87
1795517198 87
1795517203 87
1795517208 85
1795517213 85
1795517218 85
1795517223 85
1795517228 85
1795517233 85
1795517238 87
1795517243 87
1795517248 87
1795517253 87
1795517258 87
1795517263 87
1795517268 87
1795517273 87
1795517278 87
1795517283 87
1795517288 87
```
</details>

---

