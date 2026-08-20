---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 22:04:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 9 |
| Allocations | 152 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 16 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1787191147 36
1787191152 36
1787191157 36
1787191162 36
1787191167 36
1787191172 36
1787191177 36
1787191182 36
1787191187 36
1787191192 36
1787191197 36
1787191202 36
1787191207 36
1787191212 36
1787191217 36
1787191222 36
1787191227 31
1787191232 31
1787191237 31
1787191242 31
```
</details>

---

