---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-14 04:46:45 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 16-23 cores)</summary>

```
1776156086 16
1776156091 16
1776156096 16
1776156101 16
1776156106 16
1776156111 16
1776156116 16
1776156121 16
1776156126 16
1776156131 16
1776156136 18
1776156141 18
1776156146 18
1776156151 18
1776156156 18
1776156161 18
1776156166 23
1776156171 23
1776156176 18
1776156181 18
```
</details>

---

