---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 07:44:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 76-83 cores)</summary>

```
1793101137 76
1793101142 76
1793101147 82
1793101152 82
1793101157 82
1793101162 82
1793101167 82
1793101172 82
1793101177 82
1793101182 82
1793101187 82
1793101192 82
1793101197 82
1793101203 82
1793101208 82
1793101213 83
1793101218 83
1793101223 83
1793101228 83
1793101233 83
```
</details>

---

