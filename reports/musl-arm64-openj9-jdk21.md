---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 05:17:44 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 14 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787130731 48
1787130736 48
1787130741 48
1787130746 48
1787130751 48
1787130756 48
1787130761 48
1787130766 48
1787130771 48
1787130776 43
1787130781 43
1787130787 43
1787130792 43
1787130797 43
1787130802 43
1787130807 43
1787130812 43
1787130817 43
1787130822 43
1787130827 43
```
</details>

---

