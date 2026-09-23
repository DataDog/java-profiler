---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-23 10:08:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 18-22 cores)</summary>

```
1790172170 18
1790172175 18
1790172180 18
1790172186 18
1790172191 18
1790172196 18
1790172201 20
1790172206 20
1790172211 22
1790172216 22
1790172221 22
1790172226 22
1790172231 22
1790172236 22
1790172241 22
1790172246 22
1790172251 22
1790172256 22
1790172261 22
1790172266 22
```
</details>

---

