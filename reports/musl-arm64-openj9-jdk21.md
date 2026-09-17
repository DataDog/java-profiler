---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 10:30:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 10 |
| Allocations | 121 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 918 |
| Sample Rate | 15.30/sec |
| Health Score | 956% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789655061 43
1789655066 48
1789655071 48
1789655076 48
1789655081 48
1789655086 48
1789655091 48
1789655096 48
1789655101 48
1789655106 48
1789655111 48
1789655116 48
1789655121 48
1789655126 48
1789655131 48
1789655136 48
1789655141 48
1789655146 48
1789655152 48
1789655157 48
```
</details>

---

