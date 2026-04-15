---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 14:59:48 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 48-59 cores)</summary>

```
1776279133 49
1776279138 49
1776279143 49
1776279148 49
1776279153 49
1776279158 49
1776279163 49
1776279168 48
1776279173 48
1776279178 48
1776279183 54
1776279188 54
1776279193 54
1776279198 54
1776279203 59
1776279208 59
1776279213 59
1776279218 59
1776279223 59
1776279228 59
```
</details>

---

