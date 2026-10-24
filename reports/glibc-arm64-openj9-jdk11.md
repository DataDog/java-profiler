---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:16:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1792833095 34
1792833100 34
1792833105 34
1792833110 24
1792833115 24
1792833120 24
1792833125 24
1792833131 24
1792833136 24
1792833141 24
1792833146 24
1792833151 29
1792833156 29
1792833161 29
1792833166 29
1792833171 29
1792833176 29
1792833181 29
1792833186 29
1792833191 29
```
</details>

---

