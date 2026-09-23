---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 10:08:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790172186 48
1790172191 48
1790172196 48
1790172201 48
1790172206 48
1790172211 48
1790172216 48
1790172221 48
1790172226 48
1790172231 48
1790172236 48
1790172241 46
1790172246 46
1790172251 46
1790172256 46
1790172261 46
1790172266 46
1790172271 46
1790172276 46
1790172281 46
```
</details>

---

