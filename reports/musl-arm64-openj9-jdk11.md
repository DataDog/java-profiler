---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 15:18:45 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 132 |
| Sample Rate | 2.20/sec |
| Health Score | 138% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1792610096 46
1792610101 46
1792610106 46
1792610111 46
1792610116 46
1792610121 46
1792610126 46
1792610131 46
1792610136 48
1792610141 48
1792610146 48
1792610151 48
1792610156 48
1792610161 48
1792610166 48
1792610171 48
1792610176 48
1792610181 48
1792610186 48
1792610191 48
```
</details>

---

