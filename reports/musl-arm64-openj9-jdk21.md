---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-13 01:30:55 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1776058072 32
1776058077 32
1776058082 32
1776058087 32
1776058092 32
1776058097 32
1776058102 32
1776058107 32
1776058112 32
1776058117 32
1776058122 32
1776058127 32
1776058132 32
1776058137 32
1776058142 32
1776058147 32
1776058152 32
1776058157 32
1776058162 32
1776058167 32
```
</details>

---

