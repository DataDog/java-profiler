---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:15:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789686756 48
1789686761 48
1789686766 48
1789686771 48
1789686776 48
1789686781 48
1789686786 48
1789686791 48
1789686796 48
1789686801 48
1789686806 48
1789686811 48
1789686816 48
1789686821 48
1789686826 48
1789686831 48
1789686836 43
1789686841 43
1789686846 43
1789686851 43
```
</details>

---

