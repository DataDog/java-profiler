---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 08:32:07 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1792672111 31
1792672116 31
1792672121 31
1792672126 31
1792672131 31
1792672136 31
1792672141 31
1792672146 31
1792672151 31
1792672156 31
1792672161 26
1792672166 26
1792672171 26
1792672176 26
1792672181 26
1792672186 26
1792672191 26
1792672196 26
1792672201 26
1792672206 26
```
</details>

---

