---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 12:53:33 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 8 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 11 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776962882 64
1776962887 64
1776962892 64
1776962897 64
1776962902 64
1776962907 64
1776962912 64
1776962917 64
1776962922 64
1776962927 64
1776962932 64
1776962937 64
1776962942 64
1776962947 64
1776962952 64
1776962958 64
1776962963 64
1776962968 64
1776962973 64
1776962978 64
```
</details>

---

